<?php

	namespace Base\DB;

	abstract class Field {
		protected string $name;
		protected string $type;

		protected Table $table;

		protected function __construct(string $type, string $name, $table) {
			$this->name = $name;
			$this->type = $type;
			$this->table = $table;
		}

		abstract public function Check(?array $data_field_db);

		public function GetName(): string {
			return $this->name;
		}

	}