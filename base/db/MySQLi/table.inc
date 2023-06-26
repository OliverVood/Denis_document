<?php

	namespace Base\DB\MySQLi;

	class Table extends \Base\DB\Table {
		const ACTION_OK						=  1;
		const ACTION_CREATE					= -1;
		const ACTION_UPDATE					= -2;
		const ACTION_DELETE 				= -3;

		private string	$engine 			= 'InnoDB';
		private string	$encoding 			= 'utf8';
		private ?Primary $primary			= null;
		private ?Primary $primaryIndex		= null;

		/** @var DBObject $db */

		public function __construct($name, $db) {
			parent::__construct($name, $db);
		}

		public function id(string $name): void { if ($this->primary || $this->primaryIndex) { die("Table `{$this->name}` structure error! Primary key already exists."); } $this->primaryIndex = new Primary($name, [$name], $this); $this->PushField(new FieldID($name, $this)); }
		public function bool(string $name): void { $this->PushField(new FieldBool($name, $this)); }
		public function int8(string $name): void { $this->PushField(new FieldInt8($name, $this)); }
		public function int16(string $name): void { $this->PushField(new FieldInt16($name, $this)); }
		public function int24(string $name): void { $this->PushField(new FieldInt24($name, $this)); }
		public function int32(string $name): void { $this->PushField(new FieldInt32($name, $this)); }
		public function int64(string $name): void { $this->PushField(new FieldInt64($name, $this)); }
		public function uint8(string $name): void { $this->PushField(new FieldUInt8($name, $this)); }
		public function uint16(string $name): void { $this->PushField(new FieldUInt16($name, $this)); }
		public function uint24(string $name): void { $this->PushField(new FieldUInt24($name, $this)); }
		public function uint32(string $name): void { $this->PushField(new FieldUInt32($name, $this)); }
		public function uint64(string $name): void { $this->PushField(new FieldUInt64($name, $this)); }
		public function float(string $name): void { $this->PushField(new FieldFloat($name, $this)); }
		public function double(string $name): void { $this->PushField(new FieldDouble($name, $this)); }
		public function timestamp(string $name, bool $update = false): void { $this->PushField(new FieldTimestamp($name, $update, $this)); }
		public function enum(string $name, array $enum): void { $this->PushField(new FieldEnum($name, $enum, $this)); }
		public function set(string $name, array $set): void { $this->PushField(new FieldSet($name, $set, $this)); }
		public function string(string $name, int $length): void { $this->PushField(new FieldString($name, $length, $this)); }
		public function text(string $name): void { $this->PushField(new FieldText($name, $this)); }
//		public function AddPrimary(string $name, array $fields): void { if ($this->primary || $this->primaryIndex) { die("Table `{$this->name}` structure error! Primary key already exists."); } $this->primary = new Primary($name, $fields, $this); }

		private function GetFieldListApp(): array {
			$out = [];
			foreach ($this->structure as $name => $field) $out[] = $name;

			return $out;
		}

		private function GetListFieldDB(): array {
			$fieldsData = [];
			$result = $this->db->Query("SHOW FIELDS FROM `{$this->name}`");
			$fieldsList = $this->db->FetchAll($result, function(& $items, $item) use (& $fieldsData) {
				$items[] = $item['Field'];
				$fieldsData[$item['Field']] = $item;
			});

			return [$fieldsList, $fieldsData];
		}

		public function Check(): array {
			$out = ['action' => self::ACTION_OK, 'fields' => []];

			$fieldListApp = $this->GetFieldListApp();
			[$fieldListDB, $fieldsData] = $this->GetListFieldDB();
			$fields = $fieldListApp;
			foreach ($fieldListDB as $field) if (!in_array($field, $fields)) $fields[] = $field;

			foreach ($fields as $field) {

				if (!in_array($field, $fieldListDB)) {
					$out['fields'][] = ['action' => Field::ACTION_CREATE, 'name' => $field, 'error' => 'Добавить поле', 'details' => $this->structure[$field]->CreationFormat()];
					$out['action'] = self::ACTION_UPDATE;
					continue;
				}
				if (!in_array($field, $fieldListApp)) {
					$out['fields'][] = ['action' => Field::ACTION_DELETE, 'name' => $field, 'error' => 'Удалить поле'];
					$out['action'] = self::ACTION_UPDATE;
					continue;
				}

				$res = $this->structure[$field]->Check($fieldsData[$field]);

				if (!$res) {
					$out['fields'][] = ['action' => Field::ACTION_UPDATE, 'name' => $field, 'error' => 'Изменить поле', 'details' => $this->structure[$field]->UpdatingFormat()];
					$out['action'] = self::ACTION_UPDATE;
				}

			}

			return $out;
		}

		public function Make(array $fields): bool {
			foreach ($fields as $name => ['action' => $action]) {
				switch ($action) {
					case Field::ACTION_CREATE: $this->structure[$name]->Create(); break;
					case Field::ACTION_UPDATE: $this->structure[$name]->Update(); break;
					case Field::ACTION_DELETE: $this->db->Query("ALTER TABLE `{$this->name}` DROP COLUMN `{$name}`"); break;
				}
			}

			return true;
		}

		public function Create(): void {
			$fieldsList = [];
			foreach ($this->structure as $field) $fieldsList[] = $field->CreationFormat();
			$fields = implode(', ', $fieldsList);

			$after = '';
			if ($this->primaryIndex) $after .= ", PRIMARY KEY (`{$this->primaryIndex->GetFields()[0]}`)";
			$this->db->query("CREATE TABLE `{$this->name}` ({$fields}{$after}) ENGINE = {$this->engine} DEFAULT CHARSET = {$this->encoding}");
			$this->primary?->Create();
		}

	}