<?php

	namespace Base\DB;

	interface Select {
		public function table(string $table, string $as = ''): self;
		public function join(string $join, string $table, string $as = '', string $on = ''): self;
		public function fields(...$fields): self;
		public function calc(...$strings): self;
		public function where(string $where): self;
		public function group(...$fields): self;
		public function order(string $field, string $direction = 'ASC', $escape = true): self;
		public function limit(int $value_1, int $value_2 = null): self;
		public function get(): string;
	}