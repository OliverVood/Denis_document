<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt24MySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('int124', $name, $table);
		}

		public function CreationFormat(): string { return "`{$this->name}` mediumint NOT NULL DEFAULT '0'"; }

	}