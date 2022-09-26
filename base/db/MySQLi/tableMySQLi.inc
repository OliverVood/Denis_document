<?php

	namespace Base\DB;

	class TableMySQLi extends Table {
		/** @var DBMySQLi $db */

		public function __construct($name, $dbname) {
			parent::__construct($name, $dbname);
		}

		public function id(string $name) { $this->PushField(new FieldIDMySQLi($name)); }
		public function bool(string $name) { $this->PushField(new FieldBoolMySQLi($name)); }
		public function int8(string $name) { $this->PushField(new FieldInt8MySQLi($name)); }
		public function int16(string $name) { $this->PushField(new FieldInt16MySQLi($name)); }
		public function int24(string $name) { $this->PushField(new FieldInt24MySQLi($name)); }
		public function int32(string $name) { $this->PushField(new FieldInt32MySQLi($name)); }
		public function int64(string $name) { $this->PushField(new FieldInt64MySQLi($name)); }
		public function uint8(string $name) { $this->PushField(new FieldUInt8MySQLi($name)); }
		public function uint16(string $name) { $this->PushField(new FieldUInt16MySQLi($name)); }
		public function uint24(string $name) { $this->PushField(new FieldUInt24MySQLi($name)); }
		public function uint32(string $name) { $this->PushField(new FieldUInt32MySQLi($name)); }
		public function uint64(string $name) { $this->PushField(new FieldUInt64MySQLi($name)); }
		public function float(string $name) { $this->PushField(new FieldFloatMySQLi($name)); }
		public function double(string $name) { $this->PushField(new FieldDoubleMySQLi($name)); }
		public function timestamp(string $name, bool $update = false) { $this->PushField(new FieldTimestampMySQLi($name, $update)); }
		public function enum(string $name, array $enum) { $this->PushField(new FieldEnumMySQLi($name, $enum)); }
		public function set(string $name, array $set) { $this->PushField(new FieldSetMySQLi($name, $set)); }
		public function string(string $name, int $length) { $this->PushField(new FieldStringMySQLi($name, $length)); }
		public function text(string $name) { $this->PushField(new FieldTextMySQLi($name)); }

		public function Check() {
			$fields = [];

			/* Get fields DB */
			$result = $this->db->Query("SHOW COLUMNS FROM `{$this->name}` FROM `{$this->dbname}`");
			$fields_db = $this->db->FetchAll($result, function(& $items, $item) use (& $fields) {
				$items[$item['Field']] = [
					'Type' => $item['Type'],
					'Null' => $item['Null'],
					'Key' => $item['Key'],
					'Default' => $item['Default'],
					'Extra' => $item['Extra'],
				];
				$fields[] = $item['Field'];
			});

			/* Get fields struct */
			foreach ($this->structure as $name => $field) {
				if (!in_array($name, $fields)) $fields[] = $name;
			}

			/* Check fields */
			foreach ($fields as $field) {
				if (!isset($fields_db[$field])) echo "Нет поля `{$field}`.<br>";
				else if (!isset($this->structure[$field])) echo "Лишнее поле `{$field}`.<br>";
				else $this->structure[$field]->Check($fields_db[$field]);
			}

			echo "Check({$this->name});<br>";
		}

		public function Make() {
			echo "Make({$this->name});<br>";
		}

	}