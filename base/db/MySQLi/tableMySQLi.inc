<?php

	namespace Base\DB;

	class TableMySQLi extends Table {
		public function __construct($name, $dbname) {
			parent::__construct($name, $dbname);
		}

		public function Check() {
			echo "Check({$this->name});";
		}

		public function Make() {
			echo "Make({$this->name});";
		}

		public function id(string $name) { $this->Append(new FieldID($name)); }
		public function bool(string $name) { $this->Append(new FieldBool($name)); }
		public function int8(string $name) { $this->Append(new FieldInt8($name)); }
		public function int16(string $name) { $this->Append(new FieldInt16($name)); }
		public function int24(string $name) { $this->Append(new FieldInt24($name)); }
		public function int32(string $name) { $this->Append(new FieldInt32($name)); }
		public function int64(string $name) { $this->Append(new FieldInt64($name)); }
		public function uint8(string $name) { $this->Append(new FieldUInt8($name)); }
		public function uint16(string $name) { $this->Append(new FieldUInt16($name)); }
		public function uint24(string $name) { $this->Append(new FieldUInt24($name)); }
		public function uint32(string $name) { $this->Append(new FieldUInt32($name)); }
		public function uint64(string $name) { $this->Append(new FieldUInt64($name)); }
		public function float(string $name) { $this->Append(new FieldFloat($name)); }
		public function double(string $name) { $this->Append(new FieldDouble($name)); }
		public function timestamp(string $name, bool $update = false) { $this->Append(new FieldTimestamp($name, $update)); }
		public function enum(string $name, array $enum) { $this->Append(new FieldEnum($name, $enum)); }
		public function set(string $name, array $set) { $this->Append(new FieldSet($name, $set)); }
		public function string(string $name, int $length) { $this->Append(new FieldString($name, $length)); }
		public function text(string $name) { $this->Append(new FieldText($name)); }
	}