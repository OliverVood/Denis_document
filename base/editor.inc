<?php

	namespace Base;

	class Editor {
		protected string $name;

		public Action $select;

		protected function __construct($name) {
			$this->name = $name;

			$this->select = new Action($this->name, 'select');

			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
		}

		public function OnSelect() {
			Debug(123);
		}

	}