<?php

	namespace Base\DB;

	class TableMySQLi extends Table {
		/** @var DBMySQLi $db */

		public function __construct($name, $db) {
			parent::__construct($name, $db);
		}

		public function id(string $name) { $this->PushField(new FieldIDMySQLi($name, $this)); }
		public function bool(string $name) { $this->PushField(new FieldBoolMySQLi($name, $this)); }
		public function int8(string $name) { $this->PushField(new FieldInt8MySQLi($name, $this)); }
		public function int16(string $name) { $this->PushField(new FieldInt16MySQLi($name, $this)); }
		public function int24(string $name) { $this->PushField(new FieldInt24MySQLi($name, $this)); }
		public function int32(string $name) { $this->PushField(new FieldInt32MySQLi($name, $this)); }
		public function int64(string $name) { $this->PushField(new FieldInt64MySQLi($name, $this)); }
		public function uint8(string $name) { $this->PushField(new FieldUInt8MySQLi($name, $this)); }
		public function uint16(string $name) { $this->PushField(new FieldUInt16MySQLi($name, $this)); }
		public function uint24(string $name) { $this->PushField(new FieldUInt24MySQLi($name, $this)); }
		public function uint32(string $name) { $this->PushField(new FieldUInt32MySQLi($name, $this)); }
		public function uint64(string $name) { $this->PushField(new FieldUInt64MySQLi($name, $this)); }
		public function float(string $name) { $this->PushField(new FieldFloatMySQLi($name, $this)); }
		public function double(string $name) { $this->PushField(new FieldDoubleMySQLi($name, $this)); }
		public function timestamp(string $name, bool $update = false) { $this->PushField(new FieldTimestampMySQLi($name, $update, $this)); }
		public function enum(string $name, array $enum) { $this->PushField(new FieldEnumMySQLi($name, $enum, $this)); }
		public function set(string $name, array $set) { $this->PushField(new FieldSetMySQLi($name, $set, $this)); }
		public function string(string $name, int $length) { $this->PushField(new FieldStringMySQLi($name, $length, $this)); }
		public function text(string $name) { $this->PushField(new FieldTextMySQLi($name, $this)); }

		public function Check(): array {
			$out = ['state' => 1, 'fields' => []];

//			echo "Проверка таблицы <b>`{$this->name}`</b>:<br>";

			$fields = [];

			$result = $this->db->Query("SELECT `COLUMN_NAME`, `COLUMN_DEFAULT`, `IS_NULLABLE`, `DATA_TYPE`, `CHARACTER_MAXIMUM_LENGTH`, `COLUMN_TYPE`, `COLUMN_KEY`, `EXTRA` FROM information_schema.`COLUMNS` WHERE TABLE_NAME LIKE '{$this->name}' ORDER BY `ORDINAL_POSITION`");
			$fields_db = $this->db->FetchAll($result, function(& $items, $item) use (& $fields) {
				$items[$item['COLUMN_NAME']] = $item;
				$fields[] = $item['COLUMN_NAME'];
			});

			/* Get fields struct */
			foreach ($this->structure as $name => $field) {
				if (!in_array($name, $fields)) $fields[] = $name;
			}

			/* Check fields */
			foreach ($fields as $field) {
				if (!isset($fields_db[$field])) { $out['state'] = -1; $out['fields'][] = ['state' => -1, 'name' => $field->GetName()]; } //echo "Нет поля <b>`{$field}`</b>.<br>";
				else if (!isset($this->structure[$field])) { $out['state'] = -2; $out['fields'][] = ['state' => -2, 'name' => $field->GetName()]; }//echo "Лишнее поле <b>`{$field}`</b>.<br>";
				else { $res = $this->structure[$field]->Check($fields_db[$field]); if ($res['state'] < 0) $out['state'] = -3; $out['fields'][] = $res; }
			}

			return $out;
		}

		public function Make() {
			echo "Make({$this->name});<br>";
		}

	}