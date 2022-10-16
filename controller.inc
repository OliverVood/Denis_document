<?php

	namespace Base;

	class Controller {
		use Instance;

		public static $actions = [];

		public function __construct() {
			self::$actions['always']['always'] = [];
		}

		public static function PushScene(string $page, string $action, array ...$handlers) {
			for ($i = 2; $i < func_num_args(); $i++) self::$actions[$page][$action][] = func_get_arg($i);
		}

		public static function Execute() {
			$page = GetParam('__p', '__p', 'null');
			$action = GetParam('__a', '__a', 'null');

			foreach (self::$actions['always']['always'] as $handler) $handler();
			if (isset(self::$actions[$page][$action])) foreach (self::$actions[$page][$action] as $handler) $handler();
		}

	}

	Controller::init();