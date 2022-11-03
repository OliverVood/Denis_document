<?php

	namespace Base\DB;

	abstract class Table {
		protected $db;
		protected string $dbname;
		protected string $name;
		protected array $structure;

		protected function __construct($name, $db) {
			$this->db = $db;
			$this->dbname = $db->GetName();
			$this->name = $name;
			$this->structure = [];
		}

		abstract public function Check();
		abstract public function Make();

		abstract public function id(string $name): void;
		abstract public function bool(string $name): void;
		abstract public function int8(string $name): void;
		abstract public function int16(string $name): void;
		abstract public function int24(string $name): void;
		abstract public function int32(string $name): void;
		abstract public function int64(string $name): void;
		abstract public function uint8(string $name): void;
		abstract public function uint16(string $name): void;
		abstract public function uint24(string $name): void;
		abstract public function uint32(string $name): void;
		abstract public function uint64(string $name): void;
		abstract public function float(string $name): void;
		abstract public function double(string $name): void;
		abstract public function timestamp(string $name, bool $update = false): void;
		abstract public function enum(string $name, array $enum): void;
		abstract public function set(string $name, array $set): void;
		abstract public function string(string $name, int $length): void;
		abstract public function text(string $name): void;

		public function GetName(): string { return $this->name; }

		protected function PushField(Field $field): void {
			$name = $field->GetName();
			if (isset($this->structure[$name])) die('Table structure error! Field already exists.');
			$this->structure[$name] = $field;
		}

	}