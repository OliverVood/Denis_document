<?php

	namespace Base;

	class Controller {
		use Instance;

		public Stage $void;
		public Stage $work;
		public Stage $view;

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
			$area = GetParam('__a', 'null');
			$part = GetParam('__p', 'null');

			$this->void->Execute($area, $part);
			$this->work->Execute($area, $part);
			$this->view->Execute($area, $part);
		}

	}

	Controller::init();