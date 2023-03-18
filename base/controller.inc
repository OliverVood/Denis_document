<?php

	namespace Base;

	class Controller {
		use Instance;

		public Stage $init;
		public Stage $void;
		public Stage $work;
		public Stage $view;

		static public string $area = 'null';
		static public string $part = 'null';

		public function __construct() {
			$this->init = new Stage();
			$this->void = new Stage();
			$this->work = new Stage();
			$this->view = new Stage();

			self::$area = GetParam('__a', 'null');
			self::$part = GetParam('__p', 'null');
		}

		/**
		 * Выполнить контроллер
		 * @return void
		 */
		public function Execute(): void {
			$this->init->Execute(self::$area, self::$part);
			$this->void->Execute(self::$area, self::$part);
			$this->work->Execute(self::$area, self::$part);
			$this->view->Execute(self::$area, self::$part);
		}

	}

	Controller::init();