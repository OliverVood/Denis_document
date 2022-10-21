<?php

	namespace Base;

	class Stage {
		private array $actions = [];

		public function __construct() {
			$this->actions['always']['always'] = [];
		}

		public function Push(Action $action, array ...$handlers) {
			for ($i = 1; $i < func_num_args(); $i++) $this->actions[$action->area][$action->part][] = func_get_arg($i);
		}

		public function Execute($area, $part) {
			foreach ($this->actions['always']['always'] as $handler) $handler();
			if (isset($this->actions[$area][$part])) foreach ($this->actions[$area][$part] as $handler) $handler();
		}

	}