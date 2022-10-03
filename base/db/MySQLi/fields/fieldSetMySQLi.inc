<?php

	namespace Base\DB;

	use Base\DB;

	class FieldSetMySQLi extends DB\FieldMySQLi {
		private array $set;

		public function __construct(string $name, array $set, TableMySQLi $table) {
			parent::__construct('set', $name, $table);

			$this->set = $set;
		}

		protected function CreationFormat(): string { return "`{$this->name}` set('" . implode("','", $this->set) . "') NOT NULL"; }

	}