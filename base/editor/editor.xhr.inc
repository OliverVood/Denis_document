<?php

	namespace Base\Editor\XHR;

	require DIR_BASE . 'editor/editor.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base;
	use Base\Controller;
	use Base\DB\Table;
	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;
	use Base\Templates\Editor\Browse;
	use Response;
	use Closure;

	abstract class Editor extends Base\Editor\Editor {
		protected function __construct(string $name, Table $table) {
			parent::__construct($name, $table);
		}

		protected function SetHandlers(): void {
			Controller::$view->Push($this->select, Closure::fromCallable([$this, 'OnSelect']));
			Controller::$view->Push($this->browse, Closure::fromCallable([$this, 'OnBrowse']));
			Controller::$view->Push($this->create, Closure::fromCallable([$this, 'OnCreate']));
			Controller::$view->Push($this->update, Closure::fromCallable([$this, 'OnUpdate']));

			Controller::$view->Push($this->do_create, Closure::fromCallable([$this, 'DoCreate']));
			Controller::$view->Push($this->do_update, Closure::fromCallable([$this, 'DoUpdate']));
			Controller::$view->Push($this->do_delete, Closure::fromCallable([$this, 'DoDelete']));
			Controller::$view->Push($this->set_state, Closure::fromCallable([$this, 'SetState']));
		}

		#[NoReturn] protected function OnSelect(): void {
			$page = GetInt('page', 1);

			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->SelectData();
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			Response::PushHistory($this->select, array_merge(['page' => $page], $this->params));
			Response::PushSection('main', Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage));
			Response::SendJSON();
		}

		#[NoReturn] protected function OnBrowse(): void {
			$fields				= $this->FieldsBrowse();
			$navigate			= $this->NavigateBrowse();

			$id = GetInt('id');
			$item = $this->table->SelectOne(null, "(`id` = {$id})");

			Response::PushHistory($this->browse, array_merge(['id' => $id], $this->params));
			Response::PushSection('main', Browse::ToVar($this, $fields, $id, $item, "{$this->titleBrowse} #{$id}", $navigate));
			Response::SendJSON();
		}

		#[NoReturn] protected function OnCreate(): void {
			$fields				= $this->FieldsCreate();
			$navigate			= $this->NavigateCreate();

			Response::PushHistory($this->create, $this->params);
			Response::PushSection('main', Create::ToVar($this, $fields, $this->titleCreate, $navigate));
			Response::SendJSON();
		}

		#[NoReturn] protected function OnUpdate(): void {
			$id = GetInt('id');
			$item = $this->table->SelectOne(null, "(`id` = {$id})");

			$fields				= $this->FieldsUpdate();
			$navigate			= $this->NavigateUpdate();

			Response::PushHistory($this->update, array_merge(['id' => $id], $this->params));
			Response::PushSection('main', Update::ToVar($this, $fields, $id, $item, "{$this->titleUpdate} #{$id}", $navigate));
			Response::SendJSON();
		}

		#[NoReturn] protected function DoCreate(): void {
			$data = GetParam('form', []);

			$this->table->Insert($data);

			Response::PushNoticeOk($this->titleDoCreate);
			$this->OnSelect();
		}

		#[NoReturn] protected function DoUpdate(): void {
			$id = GetInt('id');
			$data = GetParam('form', []);

			$this->table->Update($data, "`id` = {$id}");

			Response::PushNoticeOk($this->titleDoUpdate);
			$this->OnSelect();
		}

		#[NoReturn] protected function DoDelete(): void {
			$id = GetInt('id');

			$this->table->Update(['state' => 100], "`id` = {$id}");

			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->SelectData();
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			Response::PushNoticeOk($this->titleDoDelete);
			Response::PushSection('main', Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage));
			Response::SendJSON();
		}

		#[NoReturn] protected function SetState(): void {
			$id = GetInt('id');
			$state = GetInt('state');
			$oldState = (int)$this->table->SelectOneField('state', "`id` = {$id}");

			if (!isset($this->states[$oldState]) || !in_array($state, $this->states[$oldState])) { Response::PushNoticeError($this->errorAccess); Response::SendJSON(); }

			$this->table->Update(['state' => $state], "`id` = {$id}");

			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->SelectData();
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			Response::PushNoticeOk($this->titleSetState);
			Response::PushSection('main', Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage));
			Response::SendJSON();
		}

	}