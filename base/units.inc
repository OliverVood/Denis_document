<?php

	namespace Base;

	abstract class Units extends Controller {
		private static array $units = [];

		public function __construct(string $file) {
			self::$units[] = [
				'name' => static::class,
				'file' => $file
			];
		}

		public static function GetUnitList(): array {
			return self::$units;
		}

	}