<?php

	namespace Base\DB;

	abstract class Field {
		protected $table;
		protected string $tablename;
		protected string $type;
		protected string $name;

		protected function __construct(string $type, string $name, $table) {
			$this->table = $table;
			$this->tablename = $table->GetName();
			$this->type = $type;
			$this->name = $name;
		}

		abstract public function Check(?array $data_field_db);
		abstract public function Make();

		public function GetName(): string {
			return $this->name;
		}

	}