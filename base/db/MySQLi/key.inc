<?php

	namespace Base\DB\MySQLi;

	abstract class Key {
		protected Table $table;

		protected string $name;
		protected array $fields = [];

		protected function __construct(string $name, array $fields, Table $table) {
			$this->table = $table;

			$this->name = $name;
			$this->fields = $fields;
		}

		abstract public function Create(): void;

	}

	require DIR_BASE . 'db/MySQLi/keys/primary.inc';