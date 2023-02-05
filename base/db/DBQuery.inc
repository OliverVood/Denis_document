<?php

	namespace Base\DB;

	abstract class DBQuery {
		protected ?bool $state;

		protected function __construct() {  }

		abstract public static function Connect();

		abstract public function Query(string $query);
		abstract public function GetQueryList(): array;

		abstract public function Insert(string $tablename, array $data): int;
		abstract public function Update(string $tablename, array $data, ?string $where): bool;
		abstract public function Delete(string $tablename, ?string $where): bool;
		abstract public function Select(string $tablename, ?array $fields, ?string $where, ?string $order, ?string $limit, ?array $calc);
		abstract public function SelectOne(string $tablename, ?array $fields, ?string $where, ?string $order, ?string $limit, ?array $calc);
		abstract public function SelectOneField(string $tablename, string $field, ?string $where, ?string $order);
		abstract public function SelectOneFieldCalc(string $tablename, string $field_calc, string $field_name, ?string $where, ?string $order);

		abstract public function Fetch($result): ?array;
		abstract public function FetchAll($result, ?callable $func = null): ?array;

		abstract protected function ConstructQueryInsert(string $tablename, array $data): string;
		abstract protected function ConstructQueryUpdate(string $tablename, array $data, ?string $where): string;
		abstract protected function ConstructQueryDelete(string $tablename, ?string $where): string;
		abstract protected function ConstructQuerySelect(string $tablename, ?array $fields, ?string $where, ?string $order, ?string $limit, ?array $calc): string;

		/**
		 * Возвращает состояние соединения
		 * @return bool
		 */
		public function State() :bool { return $this->state; }

	}