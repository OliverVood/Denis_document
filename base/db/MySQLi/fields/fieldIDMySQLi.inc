<?php

	namespace Base\DB;

	use Base\DB;

	class FieldIDMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct('id', $name, $table);
		}

		public function Check(?array $old) {
			echo "Проверка поля <b>`{$this->name}`</b><br>";
			$struct_old = $this->DefinitionType($old);

			$str_st = $this->FormatCreate();
			$str_db = $struct_old['str'];
			if (($str_st !== $str_db) || ($old['Key'] !== "PRI")) echo "Edit field <b>`{$this->name}`</b>: {$str_db}<br>";
		}

		public function Make() { echo "Make field $this->type<br>"; }

		protected function FormatCreate(): string {
			return "`{$this->name}` bigint unsigned NOT NULL AUTO_INCREMENT";
		}

		protected function DataToFormatCreate($date): string {
			$arr = [];
			$arr['name'] = "`{$date['Field']}`";
			$arr['type'] = $date['Type'];
			$arr['null'] = ($date['Null'] === 'YES') ? 'NULL' : 'NOT NULL';
			if (strripos($date['Extra'], 'auto_increment') !== false) $arr['ai'] =  'AUTO_INCREMENT';

			return implode(' ', $arr);
		}

	}