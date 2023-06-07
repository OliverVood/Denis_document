<?php

	namespace Base;

	use Closure;

	class Stage {
		private array $actions = [];

		public function __construct() {
			$this->actions['always']['always'] = [];
		}

		/**
		 * Добавить в этап обработчик
		 * @param Action $action - Действие
		 * @param Closure ...$handlers - Обработчики
		 * @return void
		 */
		public function Push(Action $action, Closure ...$handlers): void {
			foreach ($handlers as $handler) $this->actions[$action->area][$action->part][] = $handler;
		}

		/**
		 * Выполняет этап контроллера
		 * @param string $area - Область
		 * @param string $part - Часть
		 * @return void
		 */
		public function Execute(string $area, string $part): void {
			foreach ($this->actions['always']['always'] as $handler) call_user_func($handler);
			if (isset($this->actions[$area]['always'])) foreach ($this->actions[$area]['always'] as $handler) call_user_func($handler);
			if (isset($this->actions[$area][$part])) foreach ($this->actions[$area][$part] as $handler) call_user_func($handler);
		}

	}