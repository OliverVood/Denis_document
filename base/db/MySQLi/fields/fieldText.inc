<?php

	namespace Base\DB;

	use Base\DB;

	class FieldText extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('text', $name);
		}

	}