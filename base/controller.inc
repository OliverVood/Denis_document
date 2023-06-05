<?php

	namespace Base;

	abstract class Controller {
		public static Stage $init;
		public static Stage $void;
		public static Stage $work;
		public static Stage $view;

		public static string $area = 'null';
		public static string $part = 'null';

		public static function start(): void {
			self::$init = new Stage();
			self::$void = new Stage();
			self::$work = new Stage();
			self::$view = new Stage();

			self::$area = GetParam('__a', 'null');
			self::$part = GetParam('__p', 'null');
		}

		/**
		 * Выполнить контроллер
		 * @return void
		 */
		public static function Execute(): void {
			self::$init->Execute(self::$area, self::$part);
			self::$void->Execute(self::$area, self::$part);
			self::$work->Execute(self::$area, self::$part);
			self::$view->Execute(self::$area, self::$part);
		}

	}

	Controller::start();