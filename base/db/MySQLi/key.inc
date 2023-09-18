<?php

	namespace Base\DB\MySQLi;

	abstract class Key {
		protected string $type;
		protected string $name;
		protected Table $table;
		protected array $fields = [];

		protected function __construct(string $type, string $name, Table $table, array $fields) {
			$this->type = $type;
			$this->name = $name;
			$this->table = $table;
			$this->fields = $fields;
		}

		abstract public function Create(): void;

	}

	require DIR_BASE . 'db/MySQLi/keys/primary.inc';
	require DIR_BASE . 'db/MySQLi/keys/foreign.inc';