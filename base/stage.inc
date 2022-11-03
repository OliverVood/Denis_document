<?php

	namespace Base;

	class Stage {
		private array $actions = [];

		public function __construct() {
			$this->actions['always']['always'] = [];
		}

		/**
		 * Добавить в этап обработчик
		 * @param Action $action - Действие
		 * @param array ...$handlers - Обработчики
		 * @return void
		 */
		public function Push(Action $action, array ...$handlers): void {
			foreach ($handlers as $handler) $this->actions[$action->area][$action->part][] = $handler;
		}

		/**
		 * Выполняет этап контроллера
		 * @param string $area - Область
		 * @param string $part - Часть
		 * @return void
		 */
		public function Execute(string $area, string $part): void {
			foreach ($this->actions['always']['always'] as $handler) $handler();
			if (isset($this->actions[$area][$part])) foreach ($this->actions[$area][$part] as $handler) $handler();
		}

	}