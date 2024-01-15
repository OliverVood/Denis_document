<?php

	namespace Base\Editor;

	abstract class Basic {
		protected int $id;
		protected string $name;
		protected string $title;

		private static array $editors = [];

		protected function __construct(int $id, string $name, string $title) {
			$this->id = $id;
			$this->name = $name;
			$this->title = $title ?: $name;

			self::$editors[] = [
				'id' => $id,
				'name' => $name,
				'title' => $title
			];
		}

		final public static function GetEditorList(): array {
			return self::$editors;
		}

		final public static function IsExistsUnitId(int $id): bool {
			foreach (self::$editors as $editor) if ($editor['id'] == $id) return true;
			return false;
		}

	}