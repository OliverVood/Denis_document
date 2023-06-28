<?php

	namespace Base\DB\MySQLi;

	class Primary extends Key {
		public function __construct(string $name, array $fields, Table $table) {
			parent::__construct($name, $fields, $table);
		}

		public function Create(): void {
			$columns = '(`' . implode('`, `', $this->fields) . '`)';
			$this->table->Query("ALTER TABLE `{$this->table->GetName()}` ADD CONSTRAINT `{$this->name}` PRIMARY KEY {$columns};");
		}

		public function GetFields(): array {
			return $this->fields;
		}

	}