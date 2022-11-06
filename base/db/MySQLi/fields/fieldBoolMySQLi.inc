<?php

	namespace Base\DB;

	use Base\DB;

	class FieldBoolMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('bool', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` tinyint(1) NOT NULL DEFAULT '0'"; }

	}