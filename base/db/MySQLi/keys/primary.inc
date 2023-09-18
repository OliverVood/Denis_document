<?php

	namespace Base\DB\MySQLi;

	class Primary extends Key {
		public function __construct(string $name, Table $table, array $fields) {
			parent::__construct('primary', $name, $table, $fields);
		}

		public function Create(): void {
			$columns = '(`' . implode('`, `', $this->fields) . '`)';
			$this->table->Query("ALTER TABLE `{$this->table->GetName()}` ADD CONSTRAINT `{$this->name}` PRIMARY KEY {$columns};");
		}

		public function GetFields(): array {
			return $this->fields;
		}

		public function Structure(): array {
			return [
				'type' => $this->type,
				'name' => $this->name,
				'fields' => $this->fields
			];
		}

	}