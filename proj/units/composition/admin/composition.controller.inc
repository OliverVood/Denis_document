<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'composition/admin/composition.actions.inc';
	require DIR_UNITS . 'composition/admin/composition.model.inc';

	require DIR_UNITS . 'composition/admin/views/units.tpl';
	require DIR_UNITS . 'composition/admin/views/models.tpl';
	require DIR_UNITS . 'composition/admin/views/editors.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Unit;
	use Base\Instance;
	use Base\Helper\Response;
	use Base\Editor\Editor;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates as TPLS;
	use Closure;

	class Composition extends Actions\Composition {
		use Instance;

		private Model\Composition $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Composition::instance();

			self::$view->Push([self::ENTRY_XHR], self::$new_unit, Closure::fromCallable([$this, 'NewUnit']));
			self::$view->Push([self::ENTRY_XHR], self::$new_model, Closure::fromCallable([$this, 'NewModel']));
			self::$view->Push([self::ENTRY_XHR], self::$new_editor, Closure::fromCallable([$this, 'NewEditor']));
			self::$view->Push([self::ENTRY_XHR], self::$create_unit, Closure::fromCallable([$this, 'CreateUnit']));
			self::$view->Push([self::ENTRY_XHR], self::$create_model, Closure::fromCallable([$this, 'CreateModel']));
			self::$view->Push([self::ENTRY_XHR], self::$create_editor, Closure::fromCallable([$this, 'CreateEditor']));
		}

		public function GetMenu(): array {
			if (!$this->Allow(self::ACCESS_CREATE)) return [];

			return [
				self::$new_unit->GetLinkHref('Добавить единицу'),
				self::$new_model->GetLinkHref('Добавить модель'),
				self::$new_editor->GetLinkHref('Добавить редактор')
			];
		}

		#region XHR

		#[NoReturn] private function NewUnit() {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushHistory(self::$new_unit);
			Response::PushSection('main', TPLS\Composition\Units::ToVar(Unit::GetUnitList(), Editor::GetEditorList()));
			Response::SendJSON();
		}

		#[NoReturn] private function NewModel() {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushHistory(self::$new_model);
			Response::PushSection('main', TPLS\Composition\Models::ToVar(Unit::GetUnitList(), self::ROUTES));
			Response::SendJSON();
		}

		#[NoReturn] private function NewEditor() {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			Response::PushHistory(self::$new_editor);
			Response::PushSection('main', TPLS\Composition\Editors::ToVar(Unit::GetUnitList(), Editor::GetEditorList()));
			Response::SendJSON();
		}

		#[NoReturn] private function CreateUnit() {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$formData = GetParam('form');
			$data = [
				'id' => (int)$formData['id'],
				'name' => preg_replace('/[^[:alpha:]]+/', '', $formData['name']),
				'title' => preg_replace('/[^0-9a-zA-Zа-яА-ЯёЁ_ -]+/u', '', $formData['title']),
				'routes' => []
			];

			if (!$data['id']) Response::SendNoticeError('Введите номер единицы');
			if (Unit::IsExistsUnitId($data['id']) || Editor::IsExistsUnitId($data['id'])) Response::SendNoticeError('Композиция с таким номером уже существует');
			if ($data['name'] !== $formData['name']) Response::SendNoticeError('Не правильный формат названия единицы');
			if (!$data['name']) Response::SendNoticeError('Введите название единицы');
			if ($data['title'] !== $formData['title']) Response::SendNoticeError('Не правильный формат заголовка единицы');
			if (Unit::IsExistsUnitName($data['name'])) Response::SendNoticeError('Единица с таким названием уже существует');
			if (is_dir(DIR_UNITS . '/' . strtolower($data['name']))) Response::SendNoticeError('Директория для указанной единицы уже существует');

			$routes = self::ROUTES;
			foreach ($routes as $route) {
				if (!isset($formData['routes'][$route]['controller'])) continue;

				$data['routes'][$route] = [
					'binds' => 0
				];
				if (isset($formData['routes'][$route]['actions'])) $data['routes'][$route]['binds'] += self::FILE_ACTIONS;
				if (isset($formData['routes'][$route]['structure'])) $data['routes'][$route]['binds'] += self::FILE_STRUCTURE;
				if (isset($formData['routes'][$route]['model'])) $data['routes'][$route]['binds'] += self::FILE_MODEL;
			}

			$this->model->CreateUnit($data);

			Response::PushSection('main', TPLS\Composition\Units::ToVar(Unit::GetUnitList(), Editor::GetEditorList()));
			Response::PushNoticeOk("Единица «{$data['name']}» создана");
			Response::SendJSON();
		}

		#[NoReturn] private function CreateModel() {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$formData = GetParam('form');

			$nameTmp = preg_replace('/[^[:alpha:]]+/', '', $formData['name']);
			$unitId = isset($formData['unit']) ? (int)$formData['unit'] : 0;
			$routeId = isset($formData['route']) ? (int)$formData['route'] : 0;

			if ($nameTmp !== $formData['name']) Response::SendNoticeError('Не правильный формат названия модели');
			if (!$nameTmp) Response::SendNoticeError('Введите название модели');
			if (!$unitId) Response::SendNoticeError('Выберите единицу');
			if (!$routeId) Response::SendNoticeError('Выберите часть');

			$nameLower = strtolower($nameTmp);

			$unit = Unit::GetUnitByID($unitId);
			if (!$unit) Response::SendNoticeError('Выберите единицу');
			$unitName = $unit->GetName();

			$routeName = self::ROUTES[$routeId] ?? '';
			if (!$routeName) Response::SendNoticeError('Выберите часть');

			if (is_file(DIR_UNITS . "{$unitName}/{$routeName}/{$nameLower}.model.inc")) Response::SendNoticeError('Файл модели уже существует');

			$this->model->CreateModel($nameLower, $unitName, $routeName);

			Response::PushSection('main', TPLS\Composition\Models::ToVar(Unit::GetUnitList(), self::ROUTES));
			Response::PushNoticeOk("Модель «{$nameLower}» создана");
			Response::SendJSON();
		}

		#[NoReturn] private function CreateEditor() {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$formData = GetParam('form');

			$name = preg_replace('/[^[a-zA-Z_]]+/', '', $formData['name']);
			$unitId = isset($formData['unit']) ? (int)$formData['unit'] : 0;

			if ($name !== $formData['name']) Response::SendNoticeError('Не правильный формат названия редактора');
			if (!$name) Response::SendNoticeError('Введите название редактора');
			if (!$unitId) Response::SendNoticeError('Выберите единицу');

			$name = strtolower($name);

			$unit = Unit::GetUnitByID($unitId);
			if (!$unit) Response::SendNoticeError('Выберите единицу');
			$unitName = $unit->GetName();

			$editors = Editor::GetEditorList();
			if (in_array($name, array_column($editors, 'name'))) Response::SendNoticeError('Редактор уже существует');
			if (is_dir(DIR_UNITS . "{$unitName}/admin/editors/{$name}")) Response::SendNoticeError('Директория для редактора уже существует');

			$this->model->CreateEditor($name, $unitName);

			Response::PushSection('main', TPLS\Composition\Editors::ToVar(Unit::GetUnitList(), $editors));
			Response::PushNoticeOk("Редактор «{$name}» создан");
			Response::SendJSON();
		}

		#endregion XHR

	}

	Composition::init();