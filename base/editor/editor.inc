<?php

	namespace Base;

	require 'views/select.tpl';
	require 'views/create.tpl';
	require 'views/update.tpl';

	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;

	class Editor {
		protected string $name;

		public Action $select;
		public Action $create;
		public Action $update;

		protected function __construct($name) {
			$this->name = $name;

			$this->select = new Action($this->name, 'select', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/select', Admin.General.Render.ToMain); return false;");
			$this->create = new Action($this->name, 'create', 'default');
			$this->update = new Action($this->name, 'update', 'default');

			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);
		}

		public function OnSelect() {
			SendJSONSuccess(['html' => Select::object()->ToVar()]);
		}

		public function OnCreate() {
			Create::object()->ToVar();
		}

		public function OnUpdate() {
			Update::object()->ToVar();
		}

	}