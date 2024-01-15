<?php

	namespace Base;

	abstract class Controller {
		const ENTRY_HTML		= 'html';
		const ENTRY_XHR			= 'xhr';

		public static Stage $init;
		public static Stage $void;
		public static Stage $work;
		public static Stage $view;

		private static string $entry = 'null';

		public static string $area = 'null';
		public static string $part = 'null';

		/**
		 * Старт контроллера
		 * @param string $entry - Точка входа
		 * @return void
		 */
		public static function Start(string $entry): void {
			self::$entry = $entry;

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
			self::$init->Execute(self::$entry, self::$area, self::$part);
			self::$void->Execute(self::$entry, self::$area, self::$part);
			self::$work->Execute(self::$entry, self::$area, self::$part);
			self::$view->Execute(self::$entry, self::$area, self::$part);
		}

	}

	Controller::Start(ENTRY);