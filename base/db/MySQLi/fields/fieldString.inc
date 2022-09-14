<?php

	namespace Base\DB;

	use Base\DB;

	class FieldString extends DB\Field {
		private int $length;

		public function __construct(string $name, int $length) {
			parent::__construct('enum', $name);

			$this->length = $length;
		}

	}