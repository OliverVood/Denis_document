<?php

	namespace Base\DB;

	class Select extends Query {
		private array $fields			= [];
		private array $calc				= [];
		private string $table			= '';
		private array $where			= [];
		private array $group			= [];
		private array $order			= [];
		private array $limit			= [null, null];

		public function __construct() {  }

		public function fields(...$fields): self {
			foreach ($fields as $field) $this->fields[] = $field;
			return $this;
		}

		public function calc(...$strings): self {
			foreach ($strings as $string) $this->calc[] = $string;
			return $this;
		}

		public function table(string $table): self {
			$this->table = $table;
			return $this;
		}

		public function where(string $where): self {
			$this->where[] = $where;
			return $this;
		}

		public function order(string $field, string $direction = 'ASC'): self {
			$this->order[] = [$field, $direction];
			return $this;
		}

		public function group(...$fields): self {
			foreach ($fields as $field) $this->group[] = $field;
			return $this;
		}

		public function limit(int $value_1, int $value_2 = null): self {
			$this->limit = [$value_1, $value_2];
			return $this;
		}

		public function get(): string {
			$fields = [];
			foreach ($this->fields as $field) $fields[] = "`{$field}`";
			foreach ($this->calc as $string) $fields[] = $string;
			$fields = implode(', ', $fields);

			$where = $this->where ? ' WHERE ' . implode(' AND ', $this->where) : '';

			$limit = '';
			if (!is_null($this->limit[0])) $limit .= " LIMIT {$this->limit[0]}";
			if (!is_null($this->limit[1])) $limit .= ", {$this->limit[1]}";

			$order = '';
			if ($this->order) {
				$order = []; foreach ($this->order as [$field, $direction]) $order[] = "`{$field}` {$direction}";
				$order = ' ORDER BY ' . implode(', ', $order);
			}

			return "SELECT {$fields} FROM `{$this->table}`{$where}{$order}{$limit}";
		}

	}