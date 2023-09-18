<?php

	namespace Base;

	abstract class Model {
		private static array $models = [];

		protected function __construct(string $file) {
			self::$models[] = [
				'name' => static::class,
				'file' => $file
			];
		}

		public static function GetModelList(): array {
			return self::$models;
		}

	}