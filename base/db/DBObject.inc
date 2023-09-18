<?php

	namespace Base\DB;

	require DIR_BASE . 'db/DBQuery.inc';

	abstract class DBObject extends DBQuery {
		const ER_RELATIONSHIP_ONE				= 1;
		const ER_RELATIONSHIP_MANY				= 2;
		const ER_RELATIONSHIP_ONLY_ONE			= 3;
		const ER_RELATIONSHIP_ZERO_OR_ONE		= 4;
		const ER_RELATIONSHIP_ONE_OR_MANY		= 5;
		const ER_RELATIONSHIP_ZERO_OR_MANY		= 6;

		protected string $dbname;

		/** @var Table[] */ protected array $tables;

		protected function __construct() {
			parent::__construct();

			$this->tables			= [];
		}

		abstract public function Check(): array;
		abstract public function Make(): bool;
		abstract public function Structure(): array;

		public function GetName(): string {
			return $this->dbname;
		}

		public function PushTables(Table ...$tables): void {
			foreach ($tables as $table) {
				$name = $table->GetName();
				if (isset($this->tables[$name])) die('Database structure error! Table already exists.');
				$this->tables[$name] = $table;
			}
		}

		public function GetTable(string $tablename): Table {
			return $this->tables[$tablename];
		}

	}