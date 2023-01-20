<?php

	namespace Base\DB;

	abstract class DB {
		protected string $dbname;
		protected ?bool $state;

		/** @var Table[] */ protected array $tables;

		protected function __construct() {
			$this->tables			= [];
		}

		abstract public static function Connect();

		abstract public function Check(): array;
		abstract public function Make(): bool;

		abstract public function Query(string $text);
		abstract public function GetQueryList(): array;

		abstract public function Insert(string $tablename, array $data): int;
		abstract public function Update(string $tablename, array $data, ?string $where): bool;
		abstract public function Delete(string $tablename, ?string $where): bool;
		abstract public function Select(string $tablename, ?array $fields, ?string $where, ?string $order, ?string $limit, ?array $calc);

		abstract public function Fetch($result): ?array;
		abstract public function FetchAll($result, ?callable $func = null): ?array;

		abstract protected function ConstructQueryInsert(string $tablename, array $data): string;
		abstract protected function ConstructQueryUpdate(string $tablename, array $data, string $where): string;
		abstract protected function ConstructQueryDelete(string $tablename, ?string $where): string;
		abstract protected function ConstructQuerySelect(string $tablename, ?array $fields, ?string $where, ?string $order, ?string $limit, ?array $calc): string;

		public function GetName(): ?string {
			return $this->dbname;
		}

		public function PushTables(Table ...$tables) : void {
			foreach ($tables as $table) $this->tables[$table->GetName()] = $table;
		}

		public function GetTable(string $tablename): Table {
			return $this->tables[$tablename];
		}

	}