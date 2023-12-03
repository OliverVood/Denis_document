<?php

	namespace Base;

	abstract class Units extends Controller {
		private int $id;
		private string $name;

		private static array $units = [];
		private static array $ids = [];

		public function __construct(int $id, string $name, string $file) {
			$this->id = $id;
			$this->name = $name;

			self::$ids[$id] = $this;

			self::$units[] = [
				'id' => $id,
				'name' => $name,
				'file' => $file,
				'class' => static::class,
			];
		}

		public function GetName(): string {
			return $this->name;
		}

		public static function GetUnitByID(int $id): self | null {
			return self::$ids[$id] ?? null;
		}

		public static function GetUnitList(): array {
			return self::$units;
		}

		public static function IsExistsUnitId(int $id): bool {
			foreach (self::$units as $unit) if ($unit['id'] == $id) return true;
			return false;
		}

		public static function IsExistsUnitName(string $name): bool {
			foreach (self::$units as $unit) if (strtolower($unit['name']) == strtolower($name)) return true;
			return false;
		}

	}