<?php

	namespace Base\Templates;

	abstract class View {
		static private array $objects = [];

		protected function __construct() {  }

		static public function object(): static {
			$name = static::class;
			if (!isset(self::$objects[$name])) self::$objects[$name] = new static();

			return self::$objects[$name];
		}

		protected function Start(): void { ob_start(); }

		protected function Read(): string {
			$val = ob_get_contents();
			ob_end_clean();

			return $val !== false ? $val : '';
		}

	}