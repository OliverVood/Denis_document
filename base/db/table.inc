<?php

	namespace Base\DB;

	abstract class Table {
		protected string $name;
		protected ?string $dbname;
		protected array $structure;

		protected function __construct($name, $dbname) {
			$this->name = $name;
			$this->dbname = $dbname;
			$this->structure = [];
		}

		protected function Append(Field $field) {
			$name = $field->GetName();
			if (isset($this->structure[$name])) die('Table structure error! Field already exists.');
			$this->structure[$name] = $field;
		}

		abstract public function Check();
		abstract public function Make();

		abstract public function id(string $name);
		abstract public function bool(string $name);
		abstract public function int8(string $name);
		abstract public function int16(string $name);
		abstract public function int24(string $name);
		abstract public function int32(string $name);
		abstract public function int64(string $name);
		abstract public function uint8(string $name);
		abstract public function uint16(string $name);
		abstract public function uint24(string $name);
		abstract public function uint32(string $name);
		abstract public function uint64(string $name);
		abstract public function float(string $name);
		abstract public function double(string $name);
		abstract public function timestamp(string $name, bool $update = false);
		abstract public function enum(string $name, array $enum);
		abstract public function set(string $name, array $set);
		abstract public function string(string $name, int $length);
		abstract public function text(string $name);
	}