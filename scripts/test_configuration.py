"""Offline startup validation; takes the built driver path, never a real serial port."""

import subprocess
import sys
import tempfile
from pathlib import Path

import yaml


def main():
    binary = sys.argv[1]
    with tempfile.TemporaryDirectory() as directory:
        config = Path(directory) / 'd500.yaml'
        base = dict(product_name='LDLiDAR_LD19', topic_name='/d500/scan',
                    frame_id='d500_link', port_name=str(Path(directory) / 'no-device'),
                    port_baudrate=230400)
        for changes, message in (
            ({'range_min': 0.8, 'range_max': 0.6}, 'Invalid range band'),
            ({'sector_half_width_deg': 181.0}, 'Invalid range band'),
            ({'self_mask_min_deg': 260.0, 'self_mask_max_deg': 240.0}, 'Invalid self mask'),
            ({'angle_crop_max': 361.0}, 'Invalid crop bounds'),
            ({'port_baudrate': 0}, 'Invalid crop bounds'),
            ({'range_min': 0.1, 'range_max': 1.2, 'sector_mask_enabled': False,
              'self_mask_min_deg': 240.0, 'self_mask_max_deg': 260.0,
              'self_mask_range_max': 0.38, 'noise_filter_enabled': False},
             'ldlidar node start is fail'),
        ):
            config.write_text(yaml.safe_dump({'/**': {'ros__parameters': {**base, **changes}}}))
            result = subprocess.run([binary, '--ros-args', '--params-file', str(config)],
                                    capture_output=True, text=True, timeout=10)
            assert result.returncode != 0
            assert message in result.stdout + result.stderr, result.stdout + result.stderr
    print('D500 YAML startup validation passed')


if __name__ == '__main__':
    main()
