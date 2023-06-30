<?php

	namespace Base\DB;

	abstract class Table {
		protected string $name;
		protected string $description;

		protected DBObject $db;

		/** @var Field[] */ protected array $structure;

		protected function __construct($name, $db, string $description = '') {
			$this->name = $name;
			$this->description = $description;
			$this->db = $db;

			$this->structure = [];
		}

		abstract public function Check();
		abstract public function Make(array $fields): bool;
		abstract public function Structure(): array;

		abstract public function Create();

		abstract public function id(string $name, string $description): void;
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

		public function Query(string $query) {
			return $this->db->Query($query);
		}

		public function GetQueryList(): array {
			return $this->db->GetQueryList();
		}

		public function GetLastQuery(): string {
			return $this->db->GetLastQuery();
		}

		public function Insert(array $data): int {
			return $this->db->Insert($this->name, $data);
		}

		public function Update(array $data, string $where = ''): bool {
			return $this->db->Update($this->name, $data, $where);
		}

		public function Delete(string $where = ''): bool {
			return $this->db->Delete($this->name, $where);
		}

		public function Select(?array $fields = null, ?string $where = null, ?string $order = null, ?string $limit = null, ?array $calc = null) {
			return $this->db->Select($this->name, $fields, $where, $order, $limit, $calc);
		}

		public function SelectOne(?array $fields = null, ?string $where = null, ?string $order = null, ?string $limit = null, ?array $calc = null) {
			return $this->db->SelectOne($this->name, $fields, $where, $order, $limit, $calc);
		}

		public function SelectOneField(string $field, ?string $where = null, ?string $order = null) {
			return $this->db->SelectOneField($this->name, $field, $where, $order);
		}

		public function SelectOneFieldCalc(string $field_calc, string $field_name, ?string $where = null, ?string $order = null) {
			return $this->db->SelectOneFieldCalc($this->name, $field_calc, $field_name, $where, $order);
		}

		public function Fetch($result): ?array {
			return $this->db->Fetch($result);
		}

		public function FetchAll($result, ?callable $func = null): ?array {
			return $this->db->FetchAll($result, $func);
		}

		public function GetName(): string {
			return $this->name;
		}

		protected function PushField(Field $field): void {
			$name = $field->GetName();
			if (isset($this->structure[$name])) die('Table structure error! Field already exists.');
			$this->structure[$name] = $field;
		}

	}