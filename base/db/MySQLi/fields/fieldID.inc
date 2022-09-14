<?php

	namespace Base\DB;

	use Base\DB;

	class FieldID extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('id', $name);
		}

	}