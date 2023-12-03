<?php

	namespace Base\Editor;

	abstract class Basic {
		protected string $name;

		private static array $editors = [];

		protected function __construct(string $name) {
			$this->name = $name;

			self::$editors[] = [
				'name' => $name
			];
		}

		public static function GetEditorList(): array {
			return self::$editors;
		}

	}