<?php

	namespace Base;

	abstract class Units {
		private static array $names = [];
		private static array $ids = [];

		private string $name;
		private int $id;

		public function __construct(int $id, string $name) {
			$this->id = $id;
			$this->name = $name;

			self::$ids[$this->id] = $this;
			self::$names[$this->name] = $this;
		}

		/**
		 * Возвращает юнит по идентификатору
		 * @param int $id - Идентификатор
		 * @return Units
		 */
		public static function GetById(int $id): Units {
			return self::$ids[$id];
		}

		/**
		 * Возвращает юнит по названию
		 * @param string $name - Название
		 * @return Units
		 */
		public static function GetByName(string $name): Units {
			return self::$names[$name];
		}

	}