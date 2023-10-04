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
		private array $foreigners			= [];

		/** @var DBObject $db */

		public function __construct($name, $db, string $description = '') {
			parent::__construct($name, $db, $description);
		}

		public function id(string $name, string $description = ''): void { if ($this->primary || $this->primaryIndex) { die("Table `{$this->name}` structure error! Primary key already exists."); } $this->primaryIndex = new Primary($name, $this, [$name]); $this->PushField(new FieldID($name, $this, $description)); }
		public function bool(string $name, string $description = ''): void { $this->PushField(new FieldBool($name, $this, $description)); }
		public function int8(string $name, string $description = ''): void { $this->PushField(new FieldInt8($name, $this, $description)); }
		public function int16(string $name, string $description = ''): void { $this->PushField(new FieldInt16($name, $this, $description)); }
		public function int24(string $name, string $description = ''): void { $this->PushField(new FieldInt24($name, $this, $description)); }
		public function int32(string $name, string $description = ''): void { $this->PushField(new FieldInt32($name, $this, $description)); }
		public function int64(string $name, string $description = ''): void { $this->PushField(new FieldInt64($name, $this, $description)); }
		public function uint8(string $name, string $description = ''): void { $this->PushField(new FieldUInt8($name, $this, $description)); }
		public function uint16(string $name, string $description = ''): void { $this->PushField(new FieldUInt16($name, $this, $description)); }
		public function uint24(string $name, string $description = ''): void { $this->PushField(new FieldUInt24($name, $this, $description)); }
		public function uint32(string $name, string $description = ''): void { $this->PushField(new FieldUInt32($name, $this, $description)); }
		public function uint64(string $name, string $description = ''): void { $this->PushField(new FieldUInt64($name, $this, $description)); }
		public function float(string $name, string $description = ''): void { $this->PushField(new FieldFloat($name, $this, $description)); }
		public function double(string $name, string $description = ''): void { $this->PushField(new FieldDouble($name, $this, $description)); }
		public function timestamp(string $name, bool $update = false, string $description = ''): void { $this->PushField(new FieldTimestamp($name, $update, $this, $description)); }
		public function enum(string $name, array $enum, string $description = ''): void { $this->PushField(new FieldEnum($name, $enum, $this, $description)); }
		public function set(string $name, array $set, string $description = ''): void { $this->PushField(new FieldSet($name, $set, $this, $description)); }
		public function string(string $name, int $length, string $description = ''): void { $this->PushField(new FieldString($name, $length, $this, $description)); }
		public function text(string $name, string $description = ''): void { $this->PushField(new FieldText($name, $this, $description)); }
//		public function AddPrimary(string $name, array $fields): void { if ($this->primary || $this->primaryIndex) { die("Table `{$this->name}` structure error! Primary key already exists."); } $this->primary = new Primary($name, $this, $fields); }
		public function AddForeign(string $name, array $fields, string $references_table, array $references_fields, int $relationship_from = \Base\DB\DBObject::ER_RELATIONSHIP_MANY, int $relationship_to = \Base\DB\DBObject::ER_RELATIONSHIP_ONE): void { if (isset($this->foreigners[$name])) { die("Table `{$this->name}` structure error! Primary key already exists."); } $this->foreigners[] = new Foreign($name, $this, $fields, $references_table, $references_fields, $relationship_from, $relationship_to); }

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

		public function Structure(): array {
			$table = [
				'name' => $this->name,
				'description' => $this->description,
				'params' => [
					'engine' => $this->engine,
					'encoding' => $this->encoding
				],
				'fields' => [],
				'keys' => [
					'primaries' => [],
					'foreigners' => []
				]
			];
			foreach ($this->structure as $field) $table['fields'][] = $field->Structure();
			if ($this->primaryIndex) $table['keys']['primaries'][] = $this->primaryIndex->Structure();
			foreach ($this->foreigners as $foreigner) $table['keys']['foreigners'][] = $foreigner->Structure();

			return $table;
		}

	}