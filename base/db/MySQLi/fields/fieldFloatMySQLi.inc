<?php

	namespace Base\DB;

	use Base\DB;

	class FieldFloatMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('float', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` float NOT NULL DEFAULT '0'"; }

	}