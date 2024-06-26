<?php

	namespace Base\DB\MySQLi;

	class Select implements \Base\DB\Select {
		private array $fields			= [];
		private array $calc				= [];
		private string $table			= '';
		private string $as				= '';
		private string $join			= '';
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

		public function table(string $table, string $as = ''): self {
			$this->table = $table;
			if ($as) $this->as = " `{$as}`";
			return $this;
		}

		public function join(string $join, string $table, string $as = '', string $on = ''): self {
			$as = " `{$as}`";
			$this->join = " {$join} `{$table}` `{$as}` ON ({$on})";
			return $this;
		}

		public function where(string $where): self {
			$this->where[] = $where;
			return $this;
		}

		public function order(string $field, string $direction = 'ASC', $escape = true): self {
			$this->order[] = [$field, $direction, $escape];
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
				$order = []; foreach ($this->order as [$field, $direction, $escape]) $order[] = $escape ? "`{$field}` {$direction}" : "{$field} {$direction}";
				$order = ' ORDER BY ' . implode(', ', $order);
			}

			$group = $this->group ? ' GROUP BY `' . implode('`, `', $this->group) . '`' : '';

			return "SELECT {$fields} FROM `{$this->table}`{$this->as}{$this->join}{$where}{$order}{$group}{$limit}";
		}

	}