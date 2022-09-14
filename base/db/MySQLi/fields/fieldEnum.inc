<?php

	namespace Base\DB;

	use Base\DB;

	class FieldEnum extends DB\Field {
		private array $enum;

		public function __construct(string $name, array $enum) {
			parent::__construct('enum', $name);

			$this->enum = $enum;
		}

	}