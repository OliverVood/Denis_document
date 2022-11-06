<?php

	namespace Base\DB;

	use Base\DB;

	class FieldDoubleMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('double', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` double NOT NULL DEFAULT '0'"; }

	}