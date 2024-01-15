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
		 * @param array $entries - Точки входа
		 * @param Action $action - Действие
		 * @param Closure ...$handlers - Обработчики
		 * @return void
		 */
		public function Push(array $entries, Action $action, Closure ...$handlers): void {
			foreach ($handlers as $handler) $this->actions[$action->area][$action->part][] = ['handler' => $handler, 'entries' => $entries];
		}

		/**
		 * Выполняет этап контроллера
		 * @param string $entry - Точка входа
		 * @param string $area - Область
		 * @param string $part - Часть
		 * @return void
		 */
		public function Execute(string $entry, string $area, string $part): void {
			foreach ($this->actions['always']['always'] as $event) if (!$event['entries'] || in_array($entry, $event['entries'])) call_user_func($event['handler']);
			if (isset($this->actions[$area]['always'])) foreach ($this->actions[$area]['always'] as $event) if (!$event['entries'] || in_array($entry, $event['entries'])) call_user_func($event['handler']);
			if (isset($this->actions[$area][$part])) foreach ($this->actions[$area][$part] as $event) if (!$event['entries'] || in_array($entry, $event['entries'])) call_user_func($event['handler']);
		}

	}