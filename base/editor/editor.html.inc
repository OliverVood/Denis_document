<?php

	namespace Base\Editor\HTML;

	require DIR_BASE . 'editor/editor.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base;
	use Base\Controller;
	use Base\DB\Table;
	use Proj\Admin\Templates\Layout;
	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;
	use Base\Templates\Editor\Browse;
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
		}

		#[NoReturn] protected function OnSelect(): void {
			$fields				= $this->FieldsSelect();
			[$items, $ext]		= $this->SelectData();
			$navigate			= $this->NavigateSelect();
			$manage				= $this->ManageSelect();

			Layout::instance()->main->Push(Select::ToVar($this, $fields, $items, $ext, $this->titleSelect, $navigate, $manage));
		}

		#[NoReturn] protected function OnBrowse(): void {
			$fields				= $this->FieldsBrowse();
			$navigate			= $this->NavigateBrowse();

			$id = GetInt('id');
			$item = $this->table->SelectOne(null, "(`id` = {$id})");

			Layout::instance()->main->Push(Browse::ToVar($this, $fields, $id, $item, "{$this->titleBrowse} #{$id}", $navigate));
		}

		#[NoReturn] protected function OnCreate(): void {
			$fields				= $this->FieldsCreate();
			$navigate			= $this->NavigateCreate();

			Layout::instance()->main->Push(Create::ToVar($this, $fields, $this->titleCreate, $navigate));
		}

		#[NoReturn] protected function OnUpdate(): void {
			$id = GetInt('id');
			$item = $this->table->SelectOne(null, "(`id` = {$id})");

			$fields				= $this->FieldsUpdate();
			$navigate			= $this->NavigateUpdate();

			Layout::instance()->main->Push(Update::ToVar($this, $fields, $id, $item, "{$this->titleUpdate} #{$id}", $navigate));
		}

	}