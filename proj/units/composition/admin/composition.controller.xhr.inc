<?php

	namespace Proj\Admin\Units\XHR;

	require DIR_UNITS . 'composition/admin/composition.actions.inc';
	require DIR_UNITS . 'composition/admin/composition.model.inc';
	require DIR_UNITS . 'composition/admin/views/units.tpl';
	require DIR_UNITS . 'composition/admin/views/models.tpl';
	require DIR_UNITS . 'composition/admin/views/editors.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Units;
	use Base\Editor;
	use Base\Instance;
	use Proj\Admin\Actions;
	use Proj\Admin\Model;
	use Proj\Admin\Templates AS TPLS;
	use Closure;
	use Response;

	class Composition extends Actions\Composition {
		use Instance;

		private Model\Composition $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Composition::instance();

			self::$view->Push(self::$new_unit, Closure::fromCallable([$this, 'NewUnit']));
			self::$view->Push(self::$new_model, Closure::fromCallable([$this, 'NewModel']));
			self::$view->Push(self::$new_editor, Closure::fromCallable([$this, 'NewEditor']));
			self::$view->Push(self::$create_unit, Closure::fromCallable([$this, 'CreateUnit']));
			self::$view->Push(self::$create_model, Closure::fromCallable([$this, 'CreateModel']));
			self::$view->Push(self::$create_editor, Closure::fromCallable([$this, 'CreateEditor']));
		}

		#[NoReturn] private function NewUnit() {
			Response::PushHistory(self::$new_unit);
			Response::PushSection('main', TPLS\Composition\Units::ToVar(Units::GetUnitList()));
			Response::SendJSON();
		}

		#[NoReturn] private function NewModel() {
			Response::PushHistory(self::$new_model);
			Response::PushSection('main', TPLS\Composition\Models::ToVar(Units::GetUnitList(), self::ROUTES));
			Response::SendJSON();
		}

		#[NoReturn] private function NewEditor() {
			Response::PushHistory(self::$new_editor);
			Response::PushSection('main', TPLS\Composition\Editors::ToVar(Editor\Basic::GetEditorList(), Units::GetUnitList()));
			Response::SendJSON();
		}

		#[NoReturn] private function CreateUnit() {
			$formData = GetParam('form');
			$data = [
				'id' => (int)$formData['id'],
				'name' => preg_replace('/[^[:alpha:]]+/', '', $formData['name']),
				'routes' => []
			];

			if (!$data['id']) Response::SendNoticeError('Введите номер единицы');
			if (Units::IsExistsUnitId($data['id'])) Response::SendNoticeError('Единица с таким номером уже существует');
			if ($data['name'] !== $formData['name']) Response::SendNoticeError('Не правильный формат названия единицы');
			if (Units::IsExistsUnitName($data['name'])) Response::SendNoticeError('Единица с таким названием уже существует');
			if (!$data['name']) Response::SendNoticeError('Введите название единицы');
			if (!isset($formData['routes'])) Response::SendNoticeError('Выберите точку входа');
			if (is_dir(DIR_UNITS . '/' . strtolower($data['name']))) Response::SendNoticeError('Директория для указанной единицы уже существует');

			$routes = self::ROUTES;
			$entries = self::ENTRIES;
			foreach ($routes as $route) {
				if (isset($formData['routes'][$route])) {
					$data['routes'][$route] = [
						'entries' => [],
						'binds' => 0
					];
					if (isset($formData['routes'][$route]['actions'])) $data['routes'][$route]['binds'] += self::FILE_ACTIONS;
					if (isset($formData['routes'][$route]['structure'])) $data['routes'][$route]['binds'] += self::FILE_STRUCTURE;
					if (isset($formData['routes'][$route]['model'])) $data['routes'][$route]['binds'] += self::FILE_MODEL;
					foreach ($entries as $entry) {
						if (isset($formData['routes'][$route]['entries'][$entry])) {
							$data['routes'][$route]['entries'][] = $entry;
						}
					}
				}
			}

			$this->model->CreateUnit($data);

			Response::PushSection('main', TPLS\Composition\Units::ToVar(Units::GetUnitList()));
			Response::PushNoticeOk("Единица «{$data['name']}» создана");
			Response::SendJSON();
		}

		#[NoReturn] private function CreateModel() {
			$formData = GetParam('form');

			$nameTmp = preg_replace('/[^[:alpha:]]+/', '', $formData['name']);
			$unitId = isset($formData['unit']) ? (int)$formData['unit'] : 0;
			$routeId = isset($formData['route']) ? (int)$formData['route'] : 0;

			if ($nameTmp !== $formData['name']) Response::SendNoticeError('Не правильный формат названия модели');
			if (!$nameTmp) Response::SendNoticeError('Введите название модели');
			if (!$unitId) Response::SendNoticeError('Выберите единицу');
			if (!$routeId) Response::SendNoticeError('Выберите часть');

			$nameLower = strtolower($nameTmp);

			$unit = Units::GetUnitByID($unitId);
			if (!$unit) Response::SendNoticeError('Выберите единицу');
			$unitName = $unit->GetName();

			$routeName = self::ROUTES[$routeId] ?? '';
			if (!$routeName) Response::SendNoticeError('Выберите часть');

			if (is_file(DIR_UNITS . "{$unitName}/{$routeName}/{$nameLower}.model.inc")) Response::SendNoticeError('Файл модели уже существует');

			$this->model->CreateModel($nameLower, $unitName, $routeName);

			Response::PushSection('main', TPLS\Composition\Models::ToVar(Units::GetUnitList(), self::ROUTES));
			Response::PushNoticeOk("Модель «{$nameLower}» создана");
			Response::SendJSON();
		}

		#[NoReturn] private function CreateEditor() {
			$formData = GetParam('form');

			$name = preg_replace('/[^[a-zA-Z_]]+/', '', $formData['name']);
			$unitId = isset($formData['unit']) ? (int)$formData['unit'] : 0;

			if ($name !== $formData['name']) Response::SendNoticeError('Не правильный формат названия редактора');
			if (!$name) Response::SendNoticeError('Введите название редактора');
			if (!$unitId) Response::SendNoticeError('Выберите единицу');

			$name = strtolower($name);

			$unit = Units::GetUnitByID($unitId);
			if (!$unit) Response::SendNoticeError('Выберите единицу');
			$unitName = $unit->GetName();

			$editors = Editor\Basic::GetEditorList();
			if (in_array($name, array_column($editors, 'name'))) Response::SendNoticeError('Редактор уже существует');
			if (is_dir(DIR_UNITS . "{$unitName}/admin/editors/{$name}")) Response::SendNoticeError('Директория для редактора уже существует');

			$this->model->CreateEditor($name, $unitName);

			Response::PushSection('main', TPLS\Composition\Editors::ToVar($editors, Units::GetUnitList()));
			Response::PushNoticeOk("Редактор «{$name}» создан");
			Response::SendJSON();
		}

	}

	Composition::init();