<?php

	namespace Base\Templates;

	abstract class View {
		static private array $objects = [];

		protected function __construct() {  }

		/**
		 * Получение экземпляра объекта
		 * @return static
		 */
		static public function object(): static {
			$name = static::class;
			if (!isset(self::$objects[$name])) self::$objects[$name] = new static();

			return self::$objects[$name];
		}

		/**
		 * Старт буфера
		 */
		protected function Start() { ob_start(); }

		/**
		 * Получение из буфера
		 * @return string
		 */
		protected function Read(): string {
			$val = ob_get_contents();
			ob_end_clean();

			return $val !== false ? $val : '';
		}

	}