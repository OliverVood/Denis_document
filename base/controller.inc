<?php

	namespace Base;

	class Controller {
		use Instance;

		public Stage $void;
		public Stage $work;
		public Stage $view;

		static public string $area = 'null';
		static public string $part = 'null';

		public function __construct() {
			$this->void = new Stage();
			$this->work = new Stage();
			$this->view = new Stage();
		}

		/**
		 * Выполнить контроллер
		 * @return void
		 */
		public function Execute(): void {
			Controller::$area = GetParam('__a', 'null');
			Controller::$part = GetParam('__p', 'null');

			$this->void->Execute(Controller::$area, Controller::$part);
			$this->work->Execute(Controller::$area, Controller::$part);
			$this->view->Execute(Controller::$area, Controller::$part);
		}

	}

	Controller::init();