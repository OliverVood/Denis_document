<?php

	namespace Base\DB;

	abstract class Field {
		protected string $name;
		protected string $type;
		protected string $description;

		protected Table $table;

		protected function __construct(string $type, string $name, $table, string $description = '') {
			$this->name = $name;
			$this->type = $type;
			$this->description = $description;
			$this->table = $table;
		}

		abstract public function Check(array $data): bool;
		abstract public function Structure(): array;

		public function GetName(): string {
			return $this->name;
		}

	}