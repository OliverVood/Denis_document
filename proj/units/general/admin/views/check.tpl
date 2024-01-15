<?php

	namespace Proj\Admin\Templates\General;

	use Base\Templates\Buffering;

	abstract class Check {

		public static function ToVar(array $data): string {
			Buffering::Start();
			self::Render($data);
			return Buffering::Read();
		}

		public static function Render(array $data): void { ?>
			<script>
				Admin.General.Render.CheckDB(<?= json_encode($data); ?>);
			</script>
		<?php }

	}