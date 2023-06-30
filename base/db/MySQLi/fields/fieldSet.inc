<?php

	namespace Base\DB\MySQLi;

	class FieldSet extends Field {
		private array $set;

		public function __construct(string $name, array $set, Table $table, string $description) {
			parent::__construct('set', $name, $table, $description);

			$this->set = $set;

			$this->_type = ["set('" . implode("','", $this->set) . "')"];
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = null;
			$this->_extra = [''];
		}

		private function GetFormat(): string { return "`{$this->name}` set('" . implode("','", $this->set) . "') NOT NULL"; }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}