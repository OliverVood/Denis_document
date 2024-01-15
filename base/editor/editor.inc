<?php

	namespace Base\Editor;

	require DIR_BASE . 'editor/editor.actions.inc';
	require DIR_BASE . 'editor/editor.model.inc';

	require DIR_BASE . 'editor/skins/skin.inc';

	require DIR_BASE . 'editor/views/select.tpl';
	require DIR_BASE . 'editor/views/create.tpl';
	require DIR_BASE . 'editor/views/update.tpl';
	require DIR_BASE . 'editor/views/browse.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Controller;
	use Base\Helper\Response;
	use Base\Helper\Pages;
	use Base\Templates\Editor\Browse;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Update;
	use Closure;

	abstract class Editor extends Actions {
		protected Model $model;

		protected string $titleSelect = 'Выборка';
		protected string $titleBrowse = 'Просмотр';
		protected string $titleCreate = 'Создание';
		protected string $titleUpdate = 'Редактирование';
		protected string $titleDelete = 'Удалить?';
		protected string $titleState = 'Изменить состояние?';

		protected string $titleDoCreate = 'Создано';
		protected string $titleDoUpdate = 'Изменено';
		protected string $titleDoDelete = 'Удалено';
		protected string $titleSetState = 'Состояние изменено';

		protected string $errorAccess = self::TEXT_ERROR_ACCESS;

		protected array $params = [];

		protected int $page_entries = 10;

		protected function __construct(int $id, string $name, string $title = '') {
			parent::__construct($id, $name, $title);

			$this->SetHandlers();
		}

		protected function SetHandlers(): void {
			Controller::$view->Push([Controller::ENTRY_XHR], $this->select, Closure::fromCallable([$this, 'OnSelect']));
			Controller::$view->Push([Controller::ENTRY_XHR], $this->browse, Closure::fromCallable([$this, 'OnBrowse']));
			Controller::$view->Push([Controller::ENTRY_XHR], $this->create, Closure::fromCallable([$this, 'OnCreate']));
			Controller::$view->Push([Controller::ENTRY_XHR], $this->update, Closure::fromCallable([$this, 'OnUpdate']));

			Controller::$view->Push([Controller::ENTRY_XHR], $this->do_create, Closure::fromCallable([$this, 'DoCreate']));
			Controller::$view->Push([Controller::ENTRY_XHR], $this->do_update, Closure::fromCallable([$this, 'DoUpdate']));
			Controller::$view->Push([Controller::ENTRY_XHR], $this->do_delete, Closure::fromCallable([$this, 'DoDelete']));
			Controller::$view->Push([Controller::ENTRY_XHR], $this->set_state, Closure::fromCallable([$this, 'SetState']));
		}

		protected function FieldsSelect(): array { return []; }
		protected function FieldsBrowse(): array { return []; }
		protected function FieldsCreate(): array { return []; }
		protected function FieldsUpdate(): array { return []; }

//		protected function PrepareOnSelect(array & $item): void {  }
//		protected function PrepareOnBrowse(int $id, array & $item): void {  }
//		protected function PrepareOnCreate(array & $item): void {  }
		protected function PrepareOnUpdate(int $id, array & $item): void {  }

		#[NoReturn] protected function OnSelect(): void {
			if (!$this->Allow(self::ACCESS_SELECT)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$page = GetInt('page', 1);

			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->model->SelectData($page, $this->page_entries);
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			Response::PushHistory($this->select, array_merge(['page' => $page], $this->params));
			Response::PushSection('main', Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage));
			Response::SendJSON();
		}

		#[NoReturn] protected function OnBrowse(): void {
			$id = GetInt('id');

			if (!$this->Allow(self::ACCESS_BROWSE, $id)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$fields				= $this->FieldsBrowse();
			$navigate			= $this->NavigateBrowse();

			$item = $this->model->GetItem($id);

			Response::PushHistory($this->browse, array_merge(['id' => $id], $this->params));
			Response::PushSection('main', Browse::ToVar($this, $fields, $id, $item, "{$this->titleBrowse} #{$id}", $navigate));
			Response::SendJSON();
		}

		#[NoReturn] protected function OnCreate(): void {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$fields				= $this->FieldsCreate();
			$navigate			= $this->NavigateCreate();

			Response::PushHistory($this->create, $this->params);
			Response::PushSection('main', Create::ToVar($this, $fields, $this->titleCreate, $navigate, $this->params));
			Response::SendJSON();
		}

		#[NoReturn] protected function OnUpdate(): void {
			$id = GetInt('id');

			if (!$this->Allow(self::ACCESS_UPDATE, $id)) Response::SendNoticeError('Ошибка доступа');

			$item = $this->model->GetItem($id);

			$this->PrepareOnUpdate($id, $item);

			$fields				= $this->FieldsUpdate();
			$navigate			= $this->NavigateUpdate();

			Response::PushHistory($this->update, array_merge(['id' => $id], $this->params));
			Response::PushSection('main', Update::ToVar($this, $fields, $id, $item, "{$this->titleUpdate} #{$id}", $navigate, $this->params));
			Response::SendJSON();
		}

		#[NoReturn] protected function DoCreate(): void {
			if (!$this->Allow(self::ACCESS_CREATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$data = GetParam('form', []);

			$this->model->Create($data);

			Response::PushNoticeOk($this->titleDoCreate);
			$this->OnSelect();
		}

		#[NoReturn] protected function DoUpdate(): void {
			$id = GetInt('id');

			if (!$this->Allow(self::ACCESS_UPDATE, $id)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$data = GetParam('form', []);

			$this->model->Update($data, $id);

			Response::PushNoticeOk($this->titleDoUpdate);
			$this->OnSelect();
		}

		#[NoReturn] protected function DoDelete(): void {
			$id = GetInt('id');

			if (!$this->Allow(self::ACCESS_DELETE, $id)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$page = GetInt('page', 1);

			$this->model->Delete($id);

			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->model->SelectData($page, $this->page_entries);
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			Response::PushNoticeOk($this->titleDoDelete);
			Response::PushSection('main', Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage));
			Response::SendJSON();
		}

		#[NoReturn] protected function SetState(): void {
			$id = GetInt('id');

			if (!$this->Allow(self::ACCESS_STATE)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$state = GetInt('state');
			$page = GetInt('page', 1);

			$oldState = $this->model->GetState($id);
			if ($this->model->AccessState($oldState, $state)) { Response::PushNoticeError($this->errorAccess); Response::SendJSON(); }

			$this->model->SetState($state, $id);

			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->model->SelectData($page, $this->page_entries);
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			Response::PushNoticeOk($this->titleSetState);
			Response::PushSection('main', Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage));
			Response::SendJSON();
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->browse->GetLinkHrefAllow(self::ACCESS_BROWSE, 'Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->update->GetLinkHrefAllow(self::ACCESS_UPDATE, 'Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHrefAllow(self::ACCESS_DELETE, 'Удалить', array_merge(['id' => $item['id']], $this->params)); }
			];
		}

		protected function NavigateSelect(): array { return []; }
		protected function NavigateBrowse(): array { return [ function () { return $this->select->GetLinkHrefAllow(self::ACCESS_SELECT, "<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }
		protected function NavigateCreate(): array { return [ function () { return $this->select->GetLinkHrefAllow(self::ACCESS_SELECT, "<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }
		protected function NavigateUpdate(): array { return [ function () { return $this->select->GetLinkHrefAllow(self::ACCESS_SELECT, "<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }

		public function Pages($pages): string {
			if (!$this->page_entries) return '';

			return (new Pages($this->select, $pages['current'], $pages['count']))->ToString();
		}

	}