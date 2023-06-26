<?php

	namespace Base\DB\MySQLi;

	class FieldTimestamp extends Field {
		private bool $update;

		public function __construct(string $name, bool $update, Table $table) {
			parent::__construct('timestamp', $name, $table);

			$this->update = $update;

			$this->_type = 'timestamp';
			$this->_null = 'NO';
			$this->_key = '';
			$this->_default = 'CURRENT_TIMESTAMP';
			$this->_extra = $this->update ? 'DEFAULT_GENERATED on update CURRENT_TIMESTAMP' : 'DEFAULT_GENERATED';
		}

		private function GetFormat(): string { return "`{$this->name}` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP" . ($this->update ? ' ON UPDATE CURRENT_TIMESTAMP' : ''); }

		public function CreationFormat(): string { return $this->GetFormat(); }
		public function UpdatingFormat(): string { return $this->GetFormat(); }

	}